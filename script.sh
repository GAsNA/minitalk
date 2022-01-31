start=`date +%s`
./client 300900 "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean m"
end=`date +%s`

echo $((end-start))
