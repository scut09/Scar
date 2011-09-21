-- IMap接口：  killNum GetKillNum(index) 即获取指定编号玩家的杀人数

-- 脚本 需实现的函数: getPosition(index) 返回 指定编号的初始位置
--						IsWin() 返回游戏是否结束， 和四个bool值 其中获胜的设为true

function getPosition(index)

	local x = 2000
	local y = 160
	local z = 2000

	if index == 0 then
		x = -2000
		z = -2000
	elseif index == 1 then
		z = -2000
	elseif index == 2 then
		x = -2000
	end

	return x,y,z

end


function IsWin()

local player = {0,0,0,0}


	for i=1,4 do
		count = GetKillNum(i-1)

		if count >= 10 then
			player[i] = 1
			return 1,player[1],player[2],player[3],player[4]
		end
	end
	return 0,player[1],player[2],player[3],player[4]

end

