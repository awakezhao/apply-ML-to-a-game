#########################################################################
# File Name: Makefile.sh
# Author: zhaohuizhen 
# mail: 1534612574@qq.com 
# Created Time: 2017年09月24日 星期日 13时39分36秒
#########################################################################
#!/bin/bash
#!/bin/bash

test:*.o *.h
	g++ -o test *.o *.h

*.o:*.cpp *.h
	g++ -c -g *.cpp

clean:
	ls | grep -Ev "*.cpp|*.h|Makefile" | xargs rm -f;rm -f *.o Makefile.sh


