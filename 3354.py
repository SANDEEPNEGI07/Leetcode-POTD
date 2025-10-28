# Make Array Elements Equal to Zero

from typing import List 

class Solution:
    def countValidSelections(self, nums: List[int]) -> int:
        total = sum(nums)
        cases = 0
        ls = 0

        for i in range(len(nums)):
            rs = total - ls - nums[i]
            if nums[i] == 0:
                if ls == rs:
                    cases += 2
                elif ls == rs - 1 or ls - 1 == rs:
                    cases += 1
            
            ls += nums[i]
        return cases