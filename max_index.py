from math import log, ceil


def change(i, x):
    v = n - 1 + i
    d[v] = (x, d[v][1])
    while v > 0:
        v = (v - 1) // 2
        if d[2 * v + 1][0] > d[2 * v + 2][0]:
            d[v] = d[2 * v + 1]

        else:
            d[v] = d[2 * v + 2]


def sum_length(v, vleft, vright, l, r):
    if l <= vleft and vright <= r:
        return d[v]

    if vright <= l or r <= vleft:
        return (-10 ** 9 - 1, 0)

    vmed = vleft + (vright - vleft) // 2
    sum1 = sum_length(2 * v + 1, vleft, vmed, l, r)
    sum2 = sum_length(2 * v + 2, vmed, vright, l, r)
    if sum1[0] > sum2[0]:
        return sum1

    else:
        return sum2


n = int(input())
arr = list(map(int, input().split()))
remain = [(-10 ** 9 - 1, 0)] * (2 ** (ceil(log(n, 2))) - n)
for i in range(len(arr)):
    arr[i] = (arr[i], i)

arr = arr + remain
n = len(arr)
d = [0] * (n - 1) + arr

for i in range(n - 2, -1, -1):
    if d[2 * i + 1][0] > d[2 * i + 2][0]:
        d[i] = d[2 * i + 1]

    else:
        d[i] = d[2 * i + 2]

# print(d)
# print(n)
q = int(input())

for _ in range(q):
    query = input().split()
    q_type = query[0]

    if q_type == '1':
        l = int(query[1])
        r = int(query[2])
        ans = sum_length(0, 0, n, l, r + 1)
        print(ans[1])

    if q_type == '2':
        ind = int(query[1])
        x = int(query[2])
        change(ind, x)

