# -*- coding: utf-8 -*-

import os
import sys
import ConfigParser
import numpy
import operator

from collections import OrderedDict
from io import *

##########################################################################################################################################

def recommendNicheRelevantCoverage(clusterFileName, usersRatings, itemsRatings, usersTargets, globalSettings, outputFileName):

	# initialize variables
	users = len(usersRatings.keys())
	items = len(itemsRatings.keys())
	k = int(globalSettings['recommendation_size'])
	itemsRecommended = {}
	meanItemsRatings = {}
	relevantPopularity = {}
	
	# load niche of users
	usersCluster, clusterOfUsers = loadUsersCluster(clusterFileName)
	# items in dataset
	itemsDataset = itemsRatings.keys()
	
	print "Users in Niches:"
	for clusterId in clusterOfUsers.keys():
		print "N", clusterId, " -> ", len(clusterOfUsers[clusterId]), " users"
	
	itr = 0
	while (itr < k):
		# select one item from each cluster
		for clusterId in clusterOfUsers.keys():
			# users in niche
			users = clusterOfUsers[clusterId]
			# variables
			relevantPopularity = 0
			betterChoice = 0
			# items
			for itemId in itemsDataset:
				# mean notes
				if (meanItemsRatings.get(itemId,False)):
					meanItem = float(meanItemsRatings[itemId])
				else:
					ratings = numpy.array(itemsRatings[itemId].values())
					meanItemsRatings[itemId] = numpy.mean(ratings)
					meanItem = float(meanItemsRatings[itemId])
				# users with relevant feedback
				positiveFeedback, amountUsers = relevantUsers(itemsRatings, itemId, meanItem)
				relevantPopularity = len(set(positiveFeedback).intersection(set(users)))
			
				if (relevantPopularity > betterChoice):
					betterChoice = relevantPopularity
					itemSelected = itemId
			
			# remove this item
			try:
				itemsDataset.remove(itemSelected)
				# save recommendation
				itr += 1
				itemsRecommended[itr] = itemSelected
#				print itemSelected, ":", betterChoice, " -> ", clusterId
			except ValueError:
				print "Error in remove itemId", itemSelected
				
			# stopped conditional
			if (itr >= k):
				break
	
	recommendations = itemsRecommended.values()
				
	## DUMP-RECOMMENDATIONS
	with open(outputFileName, 'w') as outputFile:
		spamwriter = csv.writer(outputFile, delimiter='\t', quoting = csv.QUOTE_NONE)
		# retrieve the top K maxCoverage items not consumed by user
		cont = 0
		issuedItems = ""
		# for each item
		for i in recommendations:
			# select just k items
			if (cont < k):
				issuedItems += str(i) + ":" + str(0.0) + " "
				cont += 1
			else:
				break
		# for each user
		for u in usersTargets:
			recommendationItems = str(u) + " " + issuedItems
			spamwriter.writerow([recommendationItems])

	outputFile.close()

##########################################################################################################################################

def relevantUsers(itemsRatings, itemId, meanRatingItem):

	cont = 0
	positiveFeedback = {}
	
	for userId in itemsRatings[itemId]:
		# select relevant users
		if (itemsRatings[itemId][userId] >= meanRatingItem):
			positiveFeedback[userId] = True
			cont += 1

	return (positiveFeedback.keys(), cont)
