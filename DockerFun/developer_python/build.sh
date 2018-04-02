docker build -t developer_ptyhon .

if [ $? -eq 0 ]; then
	echo "================================================================================="
	echo "developer_python successfuly built! Now you can use it to develop SDL"
	echo "================================================================================="
fi
