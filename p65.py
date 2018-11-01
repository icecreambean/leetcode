#!/usr/bin/env python
#https:#leetcode.com/problems/valid-number/description/
#(question has a poor rating because the ambiguous spec is ridiculous)

#alternatives (in terms of learning benefit):
#  1. 11-step state machine seems cleaner: {sign, digit, point, digit, exp, (repeat)}
#       (yes, but you can merge states... this amounts to code unwrapping)
#  2. regex
#       (do it for a better question...)
#  3. learn a syntax-processing library like BeautifulSoup?

def main():
    s = Solution()
    #oldtests = {'-01 2.0 E + 9 9 .  2':True, '+3.14E+2.56':True, '3 4':True,
    #            '+ 3':True, '-.3':True}
    test = {' 123 ':True, '-0':True, '-':False, 
            '+++':False, '-+-2':False, '-2+3':False, '2.14':True, '2..1':False, 
            '2.1.1':False, '+3.14E+256':True, 
            'aa':False, '+5%':False,
            \
            "0":True, " 0.1 ":True, "abc":False, "1 a":False, "2e10":True,
            " -90e3    ":True, " 1e":False, "e3":False, " 6e-1":True, 
            " 99e2.5 ":False, "53.5e93":True, " --6 ":False, "-+3":False,
            "95a54e53":False, ".1":True, ".e1":False, "1e.66":False }
    for k in test:
        res = 'FAIL' if s.isNumber(k) != test[k] else '    '
        if res == 'FAIL':
            print('{}  "{}"'.format(res, k))
    print('All tests completed')

class Solution:
    def isNumber(self, s): #O(n)
        """
        :type s: str
        :rtype: bool
        """
        s = s.strip()
        states = {'sign':None, 'digit':0, 'point':0, 'exp':0}
        cstate = 'sign'
        for p in range(len(s)):
            is_sign = s[p] in '+-'
            is_digit = s[p].isdigit()
            is_point = s[p] == '.'
            is_exp = s[p] in 'eE'
            if is_digit: states['digit'] += 1
            #whitespace (only lstrip and rstrip allowed)
            #if s[p].isspace(): 
            #    continue
            #sign (or digit or point)
            if cstate == 'sign' and (is_sign or is_digit or (is_point and states['exp'] == 0)):
                if is_point:
                    states['point'] += 1 
                cstate = 'digit'
                continue
            #digit (or point or exp)
            if cstate == 'digit':
                if is_digit: 
                    continue
                if is_point and states['point'] == 0 and states['exp'] == 0:
                    # point after exp not allowed
                    states['point'] += 1
                    continue
                if is_exp and states['exp'] == 0 and states['digit'] > 0:
                    #note: must have had a digit before 'exp'
                    states['exp'] += 1
                    #reset for new number (no further exp allowed)
                    #states['point'] = 0    #no 'point' after exp, so no reset
                    states['digit'] = 0
                    cstate = 'sign'
                    continue
            return False
        if states['digit'] == 0: return False
        return True

if __name__ == "__main__":
    main()
