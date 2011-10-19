for file in ./*
do
	if test -f $file
	then
		t=','
		name=''
		name=$(echo $file | grep .*\\.h$)
		if [ -n $name ] && [ ${#name} -gt 2 ]
		then
			echo r\"$name\",
		fi
	fi
done
