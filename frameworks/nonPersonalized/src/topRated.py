# -*- coding: utf-8 -*-

import os
import sys
import ConfigParser
import numpy
import operator

from collections import OrderedDict
from io import *

##########################################################################################################################################

def recommendTopRated(usersRatings, itemsRatings, usersTargets, globalSettings, outputFileName):

	# initialize variables
	users = len(usersRatings.keys())
	items = len(itemsRatings.keys())	
	topRated = {}
	sortTopRated = {}
	recommendations = []
		
	# for each itemId
	for i in itemsRatings.keys():
		sumRatings = 0
		# for each userId
		for u in itemsRatings[i].keys():
			# sum of ratings
			sumRatings += itemsRatings[i][u]
		# calculate mean of ratings
		topRated[i] = sumRatings / users
		
	# generate the ranking descending of populariy
	sortTopRated = OrderedDict(sorted(topRated.items(), key=operator.itemgetter(1), reverse=True))	
	recommendations = sortTopRated.keys()
	
	## DUMP-RECOMMENDATIONS
	with open(outputFileName, 'w') as outputFile:
		spamwriter = csv.writer(outputFile, delimiter='\t', quoting = csv.QUOTE_NONE)
		# retrieve the top K maxCoverage items not consumed by user
		cont = 1
		issuedItems = ""
		# for each item
		for i in recommendations:
			# select just k items
			if (cont <= int(globalSettings['recommendation_size'])):
				issuedItems += str(i) + ":" + str(0.0) + " "
				cont += 1
			else:
				break
		# for each user
		for u in usersTargets:
			recommendationItems = str(u) + " " + issuedItems
			spamwriter.writerow([recommendationItems])

	outputFile.close()	
