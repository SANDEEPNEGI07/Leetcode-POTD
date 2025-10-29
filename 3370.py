# 3370. Smallest Number With All Set Bits

class Solution:
    def smallestNumber(self, n: int) -> int:
        result = 0
        for i in range(n + 1):
            if pow(2, i) > n:
                result = pow(2, i) - 1
                break
        return result