# -*- coding: utf-8 -*-

import os
import sys
import ConfigParser
import numpy
import operator

from collections import OrderedDict
from io import *

##########################################################################################################################################

def recommendPositiveFeedMaxCoverage(usersRatings, itemsRatings, usersTargets, globalSettings, outputFileName):

	# initialize variables
	# users = len(usersRatings.keys())
	# items = len(itemsRatings.keys())	
	popularity = {}
	usersDataset = {}
	itemsDataset = {}
	itemsMaxCov = {}
	meanItemsRatings = {}
	k = int(globalSettings['recommendation_size'])+10
#	k = 15 #testing
	usersCovering = 0
	bestCovering = 0
	score = 0
	recommendations = []
	
	# initialize with all users
#	usersCoverage = set([])
	usersCoverageSelectedItem = set([])
	itemsDataset = itemsRatings.keys()
	
	# desempate criterio:
	for i in itemsRatings.keys():
		# Popularity of an item is equal to the number of distinct users who consumed the item
		popularity[i] = len(itemsRatings[i].keys())

	itr = 0
	while (itr < k):
		# ranking of coverage
		itemId = itemsDataset[0]
		for i in itemsDataset:
			amountUsers = 0
			meanItem = 0.0
			positiveFeedback = []
			# mean rating item
			if (meanItemsRatings.get(i,False)):
				meanItem = float(meanItemsRatings[i])
			else:
				ratings = numpy.array(itemsRatings[i].values())
				meanItemsRatings[i] = numpy.mean(ratings)
				meanItem = float(meanItemsRatings[i])
			# number of covered users
			positiveFeedback, amountUsers = relevantUsers(itemsRatings, i, meanItem)
			tempCoverage = set(positiveFeedback).intersection(set(usersDataset))
			usersCovering = len(tempCoverage)
			# case is better
			if (usersCovering > bestCovering) or ((usersCovering == bestCovering) and (popularity[i] < popularity[itemId])):
				bestCovering = usersCovering
				score = bestCovering
				itemId = i
				# users coverage
				usersCoverageSelectedItem = tempCoverage

		#check if not 0
		if (score == 0):
			usersDataset = usersRatings.keys()
		else:
			#remove items recommended
			try:
				itemsDataset.remove(itemId)
				# save recommendation
				itr += 1
				itemsMaxCov[itr] = itemId
#				print itemId, ":", score
			except ValueError:
				usersDataset = usersRatings.keys()
				print "Error in remove itemId", itemId
			
			#begin the process again
			bestCovering = 0
#			usersCoverage = set(usersCoverage).union(set(usersCoverageSelectedItem))
			usersDataset = set(usersDataset) - set(usersCoverageSelectedItem)

		#case all users is covering
		if not bool(usersDataset):
			if itr < k:
				usersDataset = usersRatings.keys()
			else:
				break
				
	recommendations = itemsMaxCov.values()
	
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
