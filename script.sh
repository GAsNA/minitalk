start=`date +%s%N`
./client 7415 "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean m"
end=`date +%s%N`

echo $((end-start))
