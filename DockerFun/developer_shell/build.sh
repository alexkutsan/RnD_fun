docker build -t developer_shell .

if [ $? -eq 0 ]; then
	echo "================================================================================="
	echo "developer_shell successfuly built! Now you ca use it as base for your containers"
	echo "================================================================================="
fi
