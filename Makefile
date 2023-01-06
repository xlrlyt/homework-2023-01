
OUT=homework
xmake:
	@g++ main.cpp display.cpp kernel.cpp blockdata.cpp settingstore.cpp userstore.cpp -O2 -o $(OUT)
	@strip $(OUT)
	@echo xmake finished, output: $(OUT)
count:
	@echo -n \*pp Lines Count: 
	@find ./ -name "*pp" | xargs cat | wc -l