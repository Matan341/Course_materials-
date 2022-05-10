#!/bin/bash
chmod +x firewall.sh

if [ "$#" -ne 1 ]; then
	exit
fi

#insert stdin into txt file
cat > packets.txt

# remove space, comments and empty lines
cat $1 | grep -o '^[^#]*' | sort | uniq > rules.txt

while read line; do
	IFS=',' read -r -a subrules <<< "$line"
	the_rules=$(cat packets.txt | \
	./firewall.exe "${subrules[0]}" 2>/dev/null | \
	./firewall.exe "${subrules[1]}" 2>/dev/null| \
	./firewall.exe "${subrules[2]}" 2>/dev/null| \
	./firewall.exe "${subrules[3]}" 2>/dev/null)
	echo "$the_rules" >> output.txt
done < rules.txt

cat output.txt | grep -v "^[[:space:]]*$" | sort | uniq | tr -d " \t"

rm -f output.txt packets.txt rules.txt
