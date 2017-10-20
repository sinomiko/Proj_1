def fun_for(n):
    num=range(n)
    print num
    for w in num:
        if w<5:
            continue
        print w
fun_for(10)
