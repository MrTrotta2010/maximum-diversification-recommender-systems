# -*- coding: utf-8 -*-

import csv
import ConfigParser
import getopt
import os.path
import sys
import scipy
import numpy

from scipy.special import expit
from scipy.sparse import csr_matrix

pathname = os.path.dirname(sys.argv[0])
fullPath = os.path.abspath(pathname)

##########################################################################################################################################

def ConfigSectionMap(Config, sections):
	settings = {}
	
	for section  in sections:
		options = Config.options(section)
		
		for option in options:
			try:
				settings[option] = Config.get(section, option)
				if settings[option] == -1:
					DebugPrint("skip: %s" % option)
			except:
				print("exception on %s!" % option)
				settings[option] = None
            
	return settings

##########################################################################################################################################

def dumpRecommendations(usersRatings, k, recommendations, outputFileName):

	# open output file 
	with open(outputFileName, 'w') as outputFile:
		spamwriter = csv.writer(outputFile, delimiter='\t', quoting = csv.QUOTE_NONE)
		 
		# print header
		# spamwriter.writerow(["user_id", "itemId:rating", "itemId:rating", "..."])
			
		for user in usersRatings.keys():
			issuedItems = "" 
			for item in recommendations[user].keys():
				issuedItems += str(item) + ":" + str(recommendations[user][item]) + " "
			issuedItems = str(user) + " " + issuedItems
			spamwriter.writerow([issuedItems])
					
	outputFile.close()

##########################################################################################################################################

def loadData(inputFileName):

	# initialize dict
	usersRatings = {}
	itemsRatings = {}
	usersTimestamp = {}
	itemsTimestamp = {}
	
	# check the existence of the input file 
	if os.path.isfile(inputFileName):
		rowId = 0
		inputFile = open(inputFileName)
		
		#ignore the reader
		#inputFile.next()
		
		# for each row in data file 
		for row in inputFile:
			# split datas to ids
			values = row.split("::")
			# check the data validity
			if len(values) == int(4):
				userId = values[0]
				itemId = values[1]
				rating = float(values[2])
				timestamp = values[3]
				
				# save users rated
				if usersRatings.get(userId, False):
				    usersRatings[userId][itemId] = rating
				else:
				    usersRatings[userId] = {}
				    usersRatings[userId][itemId] = rating
				# save items rated
				if itemsRatings.get(itemId, False):
				    itemsRatings[itemId][userId] = rating
				else:
				    itemsRatings[itemId] = {}
				    itemsRatings[itemId][userId] = rating
				# save timestamp of users rated
				if usersTimestamp.get(userId, False):
				    usersTimestamp[userId][itemId] = timestamp
				else:
				    usersTimestamp[userId] = {}
				    usersTimestamp[userId][itemId] = timestamp
				# save timestamp of item rated
				if itemsTimestamp.get(itemId, False):
				    itemsTimestamp[itemId][userId] = timestamp
				else:
				    itemsTimestamp[itemId] = {}
				    itemsTimestamp[itemId][userId] = timestamp				
				
			else:
				print "\n\t***Error: Line %d has a number of descriptors different from the expected!\n" % rowId
				sys.exit(2)

			rowId += 1
			
		inputFile.close()
		
		return usersRatings, itemsRatings, usersTimestamp, itemsTimestamp
		
	else:
		print("\n\t***Error: ratings input file not found!")
		sys.exit(2)
		
##########################################################################################################################################

def loadTargets(testInput, globalSettings):

	# variables
	usersTargets = []
	
	# check the existence of the input file 
	if os.path.isfile(testInput):
		inputFile = open(testInput)
		#ignore the reader
		#inputFile.next()
		
		# 	# select usersTargets from test file
		for row in inputFile:
			# split datas to ids
			values = row.split("::")
			# check the data validity
			if len(values) == int(globalSettings['num_data_descriptors']):
				userId = values[0]
				if (not userId in usersTargets):
					usersTargets.append(userId)
		
		inputFile.close()
		
		return usersTargets
				
	else:
		print("\n\t***Error: file of users targets not found!")
		sys.exit(2)
		
##########################################################################################################################################

def loadItemsRetrieval(retrievalFile, globalSettings):

	# variables
	itemsAnalyzed = []
	
	# check the existence of the input file 
	if os.path.isfile(retrievalFile):
		inputFile = open(retrievalFile)
		#ignore the reader
		#inputFile.next()
		
		# 	# select usersTargets from test file
		for row in retrievalFile:
			# split datas to ids
			values = row.split(':')
			print values
			itemId = str(values[1])
			print "antigo: ", itemId
			itemId = itemId.replace("\n", "")
			print "novo: ", itemId
			itemsAnalyzed.append(itemId)
		
		inputFile.close()
		
		return itemsAnalyzed
				
	else:
		print("\n\t***Error: items analyzed file not found!")
		sys.exit(2)
		
##########################################################################################################################################

def loadUsersCluster(inputFileName):

	usersCluster = {}
	clusterOfUsers = {}

	# check the existence of the input file 
	if os.path.isfile(inputFileName):
		rowId = 0
		inputFile = open(inputFileName)
		
		#ignore the reader
		#inputFile.next()
		
		# for each row in data file 
		for row in inputFile:
			# split datas to ids
			row = row.rstrip()
			listElements = row.split('\t')
			userId = listElements[0]
			clusterId = listElements[1]
			# dict: userId -> clusterId
			usersCluster[userId] = clusterId

		inputFile.close()
		
		# dict: clusterID -> list of userIds
		clusters = []
		for clusterId in usersCluster.values():
			clusters.append(clusterId)
		
		for clusterId in clusters:
			# variable
			listUsers = []
			# for each user
			for userId in usersCluster.keys():
				# if user in clusterId
				if usersCluster[userId] == clusterId:
					listUsers.append(userId)
			# save in dictionary
			clusterOfUsers[clusterId] = listUsers
		
		return usersCluster, clusterOfUsers
		
	else:
		print("\n\t***Error: input file of users cluster not found!")
		sys.exit(2)	