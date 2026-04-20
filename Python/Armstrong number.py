number=int(input("Enter the number:"))
length=len(str(number))
sum=0
n=number
while(number>0):
    rem=number%10
    number=number//10
    sum=sum+(rem**length)

if (sum==n):
    print("This is a Armstrong number")
else:
    print("This is not a Armstrong number")