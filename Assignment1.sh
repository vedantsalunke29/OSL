#!/bin/sh

create() {
    echo "Enter address book name"
    read name

    res=`ls | grep -w "$name" | wc -w`

    if [ "$res" -gt 0 ]; then
        echo "Error: File is already present"
    else 
        touch "$name"
        echo "Address Book Created"
    fi
}

display() {
    echo "Enter address book name"
    read name

    res=`ls | grep -w "$name" | wc -w`

    if [ "$res" -gt 0 ]; then
        cat "$name"
    else 
        echo "Error: File is not present"
    fi
}

insert() {
    echo "Enter address book name"
    read name

    res=`ls | grep -w "$name" | wc -w`

    if [ "$res" -gt 0 ]; then
        echo "Enter Email"
        read email

        len=`grep -w "$email" "$name" | wc -w`
        if [ "$len" -gt 0 ]; then
            echo "Error: Email already exists"
        else
            echo "Enter First Name, Last Name, Mobile Number"
            read fname lname mobile
            record="$fname $lname $email $mobile"
            echo "$record" >> "$name"
            echo "Record Inserted"
        fi
    else 
        echo "Error: File is not present"
    fi
}

modify() {
    echo "Enter address book name"
    read name

    res=`ls | grep -w "$name" | wc -w`

    if [ "$res" -gt 0 ]; then
        echo "Enter Email"
        read email

        len=`grep -w "$email" "$name" | wc -w`
        if [ "$len" -gt 0 ]; then
            echo "Enter Modified First Name, Last Name, Mobile Number"
            read fname lname mobile
            new="$fname $lname $email $mobile"
            old=`grep -w "$email" "$name"`

            echo "Old Record: $old"
            echo "New Record: $new"

            sed -i '' "s/$old/$new/g" "$name"
            echo "Record Modified"
        else
            echo "Error: Email does not exist"
        fi
    else 
        echo "Error: File is not present"
    fi
}

delete() {
    echo "Enter address book name"
    read name

    res=`ls | grep -w "$name" | wc -w`

    if [ "$res" -gt 0 ]; then
        echo "Enter Email"
        read email

        len=`grep -w "$email" "$name" | wc -w`
        if [ "$len" -gt 0 ]; then
            sed -i '' "/$email/d" "$name"
            echo "Record Deleted"
        else
            echo "Error: Email does not exist"
        fi
    else 
        echo "Error: File is not present"
    fi
}

while true; do
    echo "Menu"
    echo "1. Create"
    echo "2. Display"
    echo "3. Insert"
    echo "4. Modify"
    echo "5. Delete"
    echo "6. Exit"

    echo "Enter Choice"
    read choice

    case $choice in
        1)
            create
        ;;
        2)
            display
        ;;
        3)
            insert
        ;;
        4)
            modify
        ;;
        5)
            delete
        ;;
        6)
            echo "Exiting..."
            break
        ;;
        *)
            echo "Wrong Choice"
        ;;
    esac
done
