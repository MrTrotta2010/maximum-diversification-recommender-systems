# -*- coding: utf-8 -*-

import os
import sys
import ConfigParser
import numpy
import operator
import random

from collections import OrderedDict
from io import *

##########################################################################################################################################

def recommendRandomPopularity(usersRatings, itemsRatings, usersTargets, globalSettings, percentage, outputFileName):

	# initialize variables
	users = len(usersRatings.keys())
	items = len(itemsRatings.keys())	
	popularity = {}
	sortPopularity = {}
	recommendations = []
	distribuition = []
		
	# for each itemId
	for i in itemsRatings.keys():
		# Popularity of an item is equal to the number of distinct users who consumed the item
		popularity[i] = len(itemsRatings[i].keys())
		
	# generate the ranking descending of populariy
	sortPopularity = OrderedDict(sorted(popularity.items(), key=operator.itemgetter(1), reverse=True))
	distribuition = sortPopularity.keys()
	
	# select headItems
	numberItems = int(float(items) * float(percentage))
	headItems = distribuition[:numberItems]
	
	## DUMP-RECOMMENDATIONS
	with open(outputFileName, 'w') as outputFile:
		spamwriter = csv.writer(outputFile, delimiter='\t', quoting = csv.QUOTE_NONE)
		# retrieve the top K maxCoverage items not consumed by user
		cont = 1
		issuedItems = ""
		# for each item
		while(cont <= int(globalSettings['recommendation_size'])):
			# random itemId
			while(True):
				itemId = random.choice(headItems)
				if (not(itemId in recommendations)):
					recommendations.append(itemId)
					break
			
			issuedItems += str(itemId) + ":" + str(0.0) + " "
			cont += 1
		
		# for each user
		for u in usersTargets:
			recommendationItems = str(u) + " " + issuedItems
			spamwriter.writerow([recommendationItems])

	outputFile.close()
