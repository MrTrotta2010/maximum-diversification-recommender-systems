# -*- coding: utf-8 -*-

import os
import sys
import ConfigParser
import numpy
import operator

from collections import OrderedDict
from io import *

##########################################################################################################################################

def recommendMaxCoverage(usersRatings, itemsRatings, usersTargets, globalSettings, outputFileName):

	# initialize variables
	# users = len(usersRatings.keys())
	# items = len(itemsRatings.keys())	
	usersDataset = {}
	itemsDataset = {}
	itemsMaxCov = {}
	k = int(globalSettings['recommendation_size'])
#	k = 15 #testing
	usersCovering = 0
	bestCovering = 0
	itemId = 0
	recommendations = []
	
	# initialize with all users
	usersDataset = usersRatings.keys()
	itemsDataset = itemsRatings.keys()

	itr = 0
	while (itr < k):
		# ranking of coverage
		for i in itemsDataset:
			# number of covered users
			tempCoverage = (set(itemsRatings[i].keys())).intersection(set(usersDataset))
			usersCovering = len(tempCoverage)
			# case is better
			if (usersCovering > bestCovering) or ((usersCovering == bestCovering) and (i < itemId)):
				bestCovering = usersCovering
				score = bestCovering
				itemId = i
				# users coverage
				usersCoverage = tempCoverage

		#remove users coverage
		bestCovering = 0
		usersDataset = set(usersDataset) - set(usersCoverage)
		#remove items recommended
		try:
			itemsDataset.remove(itemId)
			# save recommendation
			itr += 1
			itemsMaxCov[itr] = itemId
#			print itemId, ":", score
		except ValueError:
			usersDataset = usersRatings.keys()
			print "Error in remove itemId"

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
