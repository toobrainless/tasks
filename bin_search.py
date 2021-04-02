def bin_right(arr, x):
    L = -1
    R = len(arr)
    while L < R - 1:
        M = (L + R) // 2
        # L < R - 1 => M != L и M != R
        if arr[M] <= x:
            L = M
        else:  # elif a[M] >= X:
            R = M

    return L

input()
arr = list(map(int, input().split()))
input()
q = list(map(int, input().split()))

summ = 0
for i in q:
    ans = bin_right(arr, i)
    if arr[ans] == i:
        summ += ans
    else:
        summ -= 1


print(summ)

