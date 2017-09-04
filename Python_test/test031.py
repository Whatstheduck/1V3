#!/usr/bin/env python3
# coding: utf-8
__author__ = 'Yee_172'
__data__ = '2017/9/4'

DS = [3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 101, 102]
HS = ['caohua', 'heitao', 'fangpian', 'hongtao']

class card:
	""" Card class """
	def __init__(self, ds, hs):
		if not isinstance(ds, int) or not ds in DS:
			raise Exception('ds must in %s' % str(DS))
		if not isinstance(hs, str) or not hs in HS:
			raise Exception('hs must in %s' % str(HS))

		self.ds = ds
		self.hs = hs
