-- IMap�ӿڣ�  killNum GetKillNum(index) ����ȡָ�������ҵ�ɱ����

-- �ű� ��ʵ�ֵĺ���: getPosition(index) ���� ָ����ŵĳ�ʼλ��
--						IsWin() ������Ϸ�Ƿ������ ���ĸ�boolֵ ���л�ʤ����Ϊtrue

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


	for i=0,3 do
		count = GetKillNum(i)

		if count >= 2 then
			player[i] = 1
			return 1,player[0],player[1],player[2],player[3]
		end
	end
	return 0,player[0],player[1],player[2],player[3]

end

