ITERATIONS=200

# 1 rosenbrock
FUNCTION=1
XSPAWN=10

./build/main 2 $ITERATIONS 10 $XSPAWN $FUNCTION
python3 plot.py
./build/main 5 $ITERATIONS 10 $XSPAWN $FUNCTION
python3 plot.py
./build/main 10 $ITERATIONS 10 $XSPAWN $FUNCTION
python3 plot.py
./build/main 25 $ITERATIONS 10 $XSPAWN $FUNCTION
python3 plot.py
./build/main 25 $ITERATIONS 1 $XSPAWN $FUNCTION
python3 plot.py

# 2 drop wave
FUNCTION=2
XSPAWN=5

./build/main 2 $ITERATIONS 10 $XSPAWN $FUNCTION
python3 plot.py
./build/main 5 $ITERATIONS 10 $XSPAWN $FUNCTION
python3 plot.py
./build/main 10 $ITERATIONS 10 $XSPAWN $FUNCTION
python3 plot.py
./build/main 25 $ITERATIONS 10 $XSPAWN $FUNCTION
python3 plot.py
./build/main 25 $ITERATIONS 1 $XSPAWN $FUNCTION
python3 plot.py

# 3 levy n13 
FUNCTION=3
XSPAWN=10

./build/main 2 $ITERATIONS 10 $XSPAWN $FUNCTION
python3 plot.py
./build/main 5 $ITERATIONS 10 $XSPAWN $FUNCTION
python3 plot.py
./build/main 10 $ITERATIONS 10 $XSPAWN $FUNCTION
python3 plot.py
./build/main 25 $ITERATIONS 10 $XSPAWN $FUNCTION
python3 plot.py
./build/main 25 $ITERATIONS 1 $XSPAWN $FUNCTION
python3 plot.py

4 ackley function
FUNCTION=4
XSPAWN=30

./build/main 2 $ITERATIONS 10 $XSPAWN $FUNCTION
python3 plot.py
./build/main 5 $ITERATIONS 10 $XSPAWN $FUNCTION
python3 plot.py
./build/main 10 $ITERATIONS 10 $XSPAWN $FUNCTION
python3 plot.py
./build/main 25 $ITERATIONS 10 $XSPAWN $FUNCTION
python3 plot.py
./build/main 25 $ITERATIONS 1 $XSPAWN $FUNCTION
python3 plot.py