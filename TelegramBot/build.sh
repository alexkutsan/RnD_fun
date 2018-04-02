docker build -t telegram_bot .

if [ $? -eq 0 ]; then
	echo "================================================================================="
	echo "telegram_bot successfuly built! Now you ca use it as base for your containers"
	echo "================================================================================="
fi
