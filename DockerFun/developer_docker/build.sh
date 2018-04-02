docker build -t developer_docker .

if [ $? -eq 0 ]; then
	echo "================================================================================="
	echo "developer_docker successfuly built! Now you ca use it as base for your containers"
	echo "================================================================================="
fi
