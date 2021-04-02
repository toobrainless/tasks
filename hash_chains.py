n, q = map(int, input().split())

arr = [[] for i in range(n)]

for i in range(q):
    query = input().split()
    data = int(query[1])
    command = query[0]

    if command == 'add':
        if data not in arr[data % n]:
            arr[data % n].append(data)
        print(len(arr[data % n]))

    if command == 'find':
        if data in arr[data % n]:
            print(1)

        else:
            print(0)

    if command == 'remove':
        if data in arr[data % n]:
            print(1)

            for j in range(len(arr[data % n])):
                if arr[data % n][j] == data:
                    arr[data % n] = arr[data % n][:j] + arr[data % n][j + 1:]
                    break

        else:
            print(0)

