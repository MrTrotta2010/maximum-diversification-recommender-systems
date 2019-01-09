r='rec_softMarginRankingMF'

sed 's/\t/ /g' $r'.txt' > rec_itemKNN_tmp.txt
mv rec_itemKNN_tmp.txt $r'_conv.txt'

sed 's/\]//g' $r'.txt' > rec_itemKNN_tmp.txt
mv rec_itemKNN_tmp.txt $r'_conv.txt'

sed 's/\[//g' $r'.txt' > rec_itemKNN_tmp.txt
mv rec_itemKNN_tmp.txt $r'_conv.txt'

sed 's/:0.[0-9]\+,/:/g' $r'.txt' > rec_itemKNN_tmp.txt
mv rec_itemKNN_tmp.txt $r'_conv.txt'

sed 's/:0.[0-9]\+//g' $r'.txt' > rec_itemKNN_tmp.txt
mv rec_itemKNN_tmp.txt $r'_conv.txt'



sed 's/\t/ /g' $r'_5.txt' > rec_itemKNN_tmp.txt
mv rec_itemKNN_tmp.txt $r'_5_conv.txt'

sed 's/\]//g' $r'_5.txt' > rec_itemKNN_tmp.txt
mv rec_itemKNN_tmp.txt $r'_5_conv.txt'

sed 's/\[//g' $r'_5.txt' > rec_itemKNN_tmp.txt
mv rec_itemKNN_tmp.txt $r'_5_conv.txt'

sed 's/:0.[0-9]\+,/:/g' $r'_5.txt' > rec_itemKNN_tmp.txt
mv rec_itemKNN_tmp.txt $r'_5_conv.txt'

sed 's/:0.[0-9]\+//g' $r'_5.txt' > rec_itemKNN_tmp.txt
mv rec_itemKNN_tmp.txt $r'_5_conv.txt'



sed 's/\t/ /g' $r'_10.txt' > rec_itemKNN_tmp.txt
mv rec_itemKNN_tmp.txt $r'_10_conv.txt'

sed 's/\]//g' $r'_10.txt' > rec_itemKNN_tmp.txt
mv rec_itemKNN_tmp.txt $r'_10_conv.txt'

sed 's/\[//g' $r'_10.txt' > rec_itemKNN_tmp.txt
mv rec_itemKNN_tmp.txt $r'_10_conv.txt'

sed 's/:0.[0-9]\+,/:/g' $r'_10.txt' > rec_itemKNN_tmp.txt
mv rec_itemKNN_tmp.txt $r'_10_conv.txt'

sed 's/:0.[0-9]\+//g' $r'_10.txt' > rec_itemKNN_tmp.txt
mv rec_itemKNN_tmp.txt $r'_10_conv.txt'



sed 's/\t/ /g' $r'_20.txt' > rec_itemKNN_tmp.txt
mv rec_itemKNN_tmp.txt $r'_20_conv.txt'

sed 's/\]//g' $r'_20.txt' > rec_itemKNN_tmp.txt
mv rec_itemKNN_tmp.txt $r'_20_conv.txt'

sed 's/\[//g' $r'_20.txt' > rec_itemKNN_tmp.txt
mv rec_itemKNN_tmp.txt $r'_20_conv.txt'

sed 's/:0.[0-9]\+,/:/g' $r'_20.txt' > rec_itemKNN_tmp.txt
mv rec_itemKNN_tmp.txt $r'_20_conv.txt'

sed 's/:0.[0-9]\+//g' $r'_20.txt' > rec_itemKNN_tmp.txt
mv rec_itemKNN_tmp.txt $r'_20_conv.txt'
