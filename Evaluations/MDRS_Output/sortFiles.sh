cd $2/alfa$1/$3/
sudo rm acc.txt
sort -f -r -k2 eval.txt > acc.txt
chmod 777 acc.txt
sudo rm acc_rel.txt
sort -f -r -k3 eval.txt > acc_rel.txt
chmod 777 acc_rel.txt
sudo rm div.txt
sort -f -r -k4 eval.txt > div.txt
chmod 777 div.txt
cd ../../
