echo "\nRunning unit tests:"

for i in tests/*_tests
do
    if test -f $i
    then
        echo "\nTest #1: print_a_message alin 2"
        if $VALGRIND ./$i ./build/libex29.so print_a_message "alin" 2 2>> tests/tests.log
        then
            echo $i "(print_a_message.1)" PASS
        else
            echo "ERROR in test $i (print_a_message.1) : here's tests/tests.log"
            echo "-------"
            tail tests/tests.log
            exit 1
        fi   
        
        echo "\nTest #2: print_a_message alin 8"
        if $VALGRIND ./$i ./build/libex29.so print_a_message "alin" 8 2>> tests/tests.log
        then
            echo $i "(print_a_message.2)" PASS
        else
            echo "ERROR in test $i (print_a_message.2) : here's tests/tests.log"
            echo "-------"
            tail tests/tests.log
            exit 1
        fi   
                    
        echo "\nTest #3: uppercase HellO ThErE 6"
        if $VALGRIND ./$i ./build/libex29.so uppercase "HellO ThErE" 6 2>> tests/tests.log
        then
            echo $i "(uppercase.1)" PASS
        else
            echo "ERROR in test $i (uppercase.1) : here's tests/tests.log"
            echo "-------"
            tail tests/tests.log
            exit 1
        fi   
               
        echo "\nTest #4: uppercase HellO ThErE 100"
        if $VALGRIND ./$i ./build/libex29.so uppercase "HellO ThErE" 100 2>> tests/tests.log
        then
            echo $i "(uppercase.2)" PASS
        else
            echo "ERROR in test $i (uppercase.2) : here's tests/tests.log"
            echo "-------"
            tail tests/tests.log
            exit 1
        fi   

        echo "\nTest #5: lowercase HellO ThErE 7"
        if $VALGRIND ./$i ./build/libex29.so lowercase "HellO ThErE" 7 2>> tests/tests.log
        then
            echo $i "(lowercase.1)" PASS
        else
            echo "ERROR in test $i (lowercase.1) : here's tests/tests.log"
            echo "-------"
            tail tests/tests.log
            exit 1
        fi   
        
        echo "\nTest #6: lowercase HellO ThErE 20"
        if $VALGRIND ./$i ./build/libex29.so lowercase "HellO ThErE" 20 2>> tests/tests.log
        then
            echo $i "(lowercase.2)" PASS
        else
            echo "ERROR in test $i (lowercase.2) : here's tests/tests.log"
            echo "-------"
            tail tests/tests.log
            exit 1
        fi   
        
        echo "\nTest #7: fail_on_purpose I failed 8" 
        if $VALGRIND ./$i ./build/libex29.so fail_on_purpose "I failed" 8 2>> tests/tests.log
        then
            echo $i "(fail_on_purpose)" PASS
        else
            echo "ERROR in test $i (fail_on_purpose) : here's tests/tests.log"
            echo "-------"
            echo "But it's on purpose so it's OK!"
        fi
    fi
done

echo ""
