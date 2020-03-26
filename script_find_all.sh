# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    script_2.sh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nabih <naali@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/11 17:56:03 by nabih             #+#    #+#              #
#    Updated: 2020/02/28 15:25:52 by chcoutur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

find . -name "*.cor" -delete
FILES=( $(find . -name "*.s") )
indice=0
max=${#FILES[@]}
flg=0
CoreFile=""

while [ $indice -lt $max ]
do
	# touch "my_test"
	# touch "og_test"
	flg=0
	./asm ${FILES[$indice]}
	CoreFile="${FILES[$indice]::${#FILES[$indice]} - 2}.cor"
	echo $CoreFile
	if [[ -f $CoreFile ]]; then
		hexdump $CoreFile > "my_test"
	fi
	./asm_zaz ${FILES[$indice]}
	if [[ -f $CoreFile ]]; then
		hexdump $CoreFile > "og_test"
	fi
	if [[ -f $CoreFile ]]
	then
		echo "Diff: START"
		diff -uN my_test og_test
		echo "Diff: END"
	fi
	indice=$((indice + 1))
	echo ""
done

rm -f "my_test"
rm -f "og_test"
find . -name "*.cor" -delete
