#!/usr/bin/env python3
# coding: utf-8
__author__ = 'Yee_172'
__data__ = '2017/9/4'

import io
import sys

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')
# change encoding into utf-8 for correctly printing

POINTS = [3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 101, 102]
POINTS_SHOW = {3: '3', 4: '4', 5: '5', 6: '6', 7: '7', 8: '8', 9: '9', 10: '10', 11: 'J',\
			   12: 'Q', 13: 'K', 14: 'A', 15: '2', 101: 'Joker', 102: '\033[1;31mJoker\033[0m'}
POINTS_FULL = {3: 'three', 4: 'four', 5: 'five', 6: 'six', 7: 'seven', 8: 'eight', 9: 'nine',\
			   10: 'ten', 11: 'jack', 12: 'queen', 13: 'king', 14: 'ace', 15: 'two',\
			   101: 'joker', 102: '\033[1;31mjoker\033[0m'}
SUITS = ['D', 'C', 'H', 'S']
SUITS_SHOW = {'D': '\033[1;31m♦\033[0m', 'C': '♣', 'H': '\033[1;31m♥\033[0m', 'S': '♠'}
SUITS_FULL = {'D': 'diamond', 'C': 'club', 'H': 'heart', 'S': 'spade'}


class Card:
	""" Card class """
	def __init__(self, point, suit=None):
		if point not in POINTS:
			raise Exception('Point must in %s!' % str(POINTS))
		if point in POINTS[-2:] and suit is not None:
			raise Exception('Joker has no suit!')
		if point in POINTS[:-2] and suit.upper() not in SUITS:
			raise Exception('Suit must in %s!' % str(SUITS).replace('\'', ''))

		suit = suit if suit is None else suit.upper()
		self.suit = suit
		self.point = point

	def __str__(self, mode='SHOW'):
		""" Return a string represent itself """
		mode = mode.upper()
		if mode not in ['SHOW', 'FULL']:
			raise Exception('Mode must in [SHOW, FULL]!')

		if mode == 'SHOW':
			return POINTS_SHOW[self.point] if self.suit is None\
				else SUITS_SHOW[self.suit] + POINTS_SHOW[self.point]
		if mode == 'FULL':
			return POINTS_FULL[self.point] if self.suit is None\
				else 'the ' + POINTS_FULL[self.point] + ' of ' + SUITS_FULL[self.suit]
