#/bin/sh

rm *.txt *.dat > /dev/null

path="log.olaDyMFlow"

echo Time.txt temp.txt
awk '{if($0~/Time = /) print $0 >> "temp.txt"}' $path;
awk '{if(NR % 2 !=0) printf "%6f\n",$3 >>"Time.txt"}' ./temp.txt
#awk '{if(NR % 2 !=0) print $0 >> "new.txt" }' ./Time_40.txt
rm ./temp.txt

echo LinearVel.txt temp22.txt temp2.txt
awk  '{if($0~/Linear velocity/)printf "%s %s %s\r\n", $3,$4,$5 >>"temp22.txt"}' $path
awk '{if(NR % 1 ==0) print; }' temp22.txt > temp2.txt 
awk '{gsub(/[()]/,""); print;}' temp2.txt > LinearVel.txt
rm temp22.txt temp2.txt

echo AngularVel.txt temp3.txt temp33.txt
awk  '{if($0~/Angular velocity/)printf "%s %s %s\r\n", $3,$4,$5 >>"temp33.txt"}' $path
awk '{if(NR % 1 ==0) print;}' temp33.txt > temp3.txt
awk '{gsub(/[()]/,""); print;}' temp3.txt > AngularVel.txt
rm temp33.txt temp3.txt

echo Displacement.txt temp4.txt temp44.txt
awk '{if($0~/Centre of mass/) printf "%s %s %s\r\n", $4, $5, $6>>"temp44.txt"}' $path
awk '{if(NR %1 ==0) print;}' temp44.txt > temp4.txt
awk '{gsub(/[()]/,""); print;}' temp4.txt > Displacement.txt
rm temp4.txt temp44.txt

echo AngularDisp.txt temp4.txt temp44.txt
awk '{if($0~/Orientation/) printf "%s %s %s %s %s %s %s %s %s\r\n", $2,$3,$4,$5,$6,$7,$8,$9,$10>>"temp44.txt"}' $path
awk '{if(NR %1 ==0) print;}' temp44.txt > temp4.txt
awk '{gsub(/[()]/,""); print;}' temp4.txt > AngularDisp.txt
rm temp4.txt temp44.txt


echo CenterRotation.txt temp5.txt temp55.txt
awk '{if($0~/Centre of rotation/) printf "%s %s %s\r\n", $4, $5, $6>>"temp55.txt"}' $path
awk '{if(NR % 1 ==0) print;}' temp55.txt > temp5.txt
awk '{gsub(/[()]/,""); print;}' temp5.txt > CenterRotation.txt
rm temp5.txt temp55.txt

paste Time.txt LinearVel.txt > linear_time.dat
paste Time.txt Displacement.txt > displacement_time.dat
