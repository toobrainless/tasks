def find(data):
    i = data % n

    while arr[i] != data:
        if arr[i] is None:
            return 0

        i = (i + 1) % n

    return 1


n, q = map(int, input().split())

arr = [None] * n

for i in range(q):
    query = input().split()
    data = int(query[1])
    command = query[0]

    if command == 'add':
        i = data % n
        flag = 1
        while arr[i] != data:
            if arr[i] == 'deleted':
                arr[i] = data
                print(i)
                flag = 0
                break

            if arr[i] is None:
                arr[i] = data
                print(i)
                flag = 0
                break

            i = (i + 1) % n

        if flag:
            print(i)

    if command == 'find':
        if find(data) > 0:
            print(1)

        else:
            print(0)

    if command == 'remove':
        if find(data):
            i = data % n
            while arr[i] != data:
                i = (i + 1) % n

            arr[i] = 'deleted'
            print(1)

        else:
            print(0)

