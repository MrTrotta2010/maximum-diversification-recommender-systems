# -*- coding: utf-8 -*-

import os
import sys
import ConfigParser
import numpy
import operator

from collections import OrderedDict
from io import *

##########################################################################################################################################

def recommendNicheCoverage(clusterFileName, usersRatings, itemsRatings, usersTargets, globalSettings, outputFileName):

	# initialize variables
	users = len(usersRatings.keys())
	items = len(itemsRatings.keys())
	k = int(globalSettings['recommendation_size'])+5
	itemsRecommended = {}
	popularity = {}
	
	# load niche of users
	usersCluster, clusterOfUsers = loadUsersCluster(clusterFileName)
	# items in dataset
	itemsDataset = itemsRatings.keys()	
	
	itr = 0
	while (itr < k):
		# select one item from each cluster
		for clusterId in clusterOfUsers.keys():
			# users in niche
			users = clusterOfUsers[clusterId]
			# variables
			popularityInNiche = 0
			betterChoice = 0
			# items remaining
			for itemId in itemsDataset:
				# popularity
				popularityInNiche = len(set(itemsRatings[itemId].keys()).intersection(set(users)))
							
				if (popularityInNiche > betterChoice):
					betterChoice = popularityInNiche
					itemSelected = itemId
			
			# remove this item
			try:
				itemsDataset.remove(itemSelected)
				# save recommendation
				itr += 1
				itemsRecommended[itr] = itemSelected
				print itemSelected, ":", betterChoice, " -> ", clusterId
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
