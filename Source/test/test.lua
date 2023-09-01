print("this is test.lua")
--t = Test()
t:Print()

print(t:GetData())
t.data = 3
--print(t:GetData())
t:PrintData()

t:SetData(6)
t:PrintData()

print("call SetData..........")
t:SetData(10, 0)
print(t:GetData())


print("tt -----------------")
print(tt.GetData(tt))
tt.SetData(tt, 100)
tt:PrintData(tt)
