#!/bin/bash 
chmod +x scrape_players.sh

BASE_URL="https://www.premierleague.com"
wget https://www.premierleague.com/players 
grep -E -o "/players/([0-9]*)/([A-Za-z-]*)/overview" players > urls.txt 
rm players
TOT_PLAYERS=$(wc -l < urls.txt) 
echo "Total players:"$TOT_PLAYERS > player_results.csv
while read line; do
    name=$line
    NEW_URL="${BASE_URL}${name}"
    wget $NEW_URL
    grep -o -i midfielder overview > freq.txt
    counter=$(wc -l < freq.txt)   
    (($counter > 0)) && echo "$NEW_URL, Midfielder," $counter >> player_results.csv
    rm overview
    rm freq.txt
done < urls.txt

rm urls.txt






