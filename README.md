Project Name: Library Management System
Group Name: Prime Coders
Programming Tier: Tier - 2
Programming Approach: Object - Oriented Programming Approach
Date: 29 - Dec - 2024

Schema of a Files:

1. userdetails.DAT
Suppose, userCount (4 bytes) = 1 
	   totalCount (4 bytes) = 3 
	    username (30 bytes) = saqib_niazi	(Member of Authentication Class)
	    password (30 bytes) = 123@	      (Member of Authentication Class)

---------------------------------------------------
13saqib_niazi123@	                       
---------------------------------------------------

****************************************

2. bookdetails.DAT
Suppose, bookCount (4 bytes) = 1
	         bookId  (4 bytes) = 222 
	               title (30 bytes) = Science	     (Member of Book Class)
                author (30 bytes) = Robert	     (Member of Book Class)
             isAvailable (1 byte) = 1		         (Member of Book Class)

-----------------------------------------
1222ScienceRobert1               
-----------------------------------------

*****************************************

3. memberdetails.DAT
Suppose, memberCount (4 bytes) = 1 
	                 name (30 bytes) = Usman 		  (Member of Library Class)
	               memberId (4 bytes) = 111	     	(Member of Member Class)
            		regNo   (25 bytes) = 4924	    	(Member of Member Class)

-----------------------------------------
1Usman1114924                    
-----------------------------------------

******************************************

4. reportdetails.DAT
Suppose, reportCount (4 bytes) = 1
	      memberId (4 bytes) = 222  (Member of Report Struct)
                       bookId (4 bytes) = 555  (Member of Report Struct)

-----------------------------------------
1222555               
-----------------------------------------

*****************************************

References:

1. ChatGPT (https://chatgpt.com/)
2. Stack over flow (https://stackoverflow.com/)
3. Geeks for geeks (https://www.geeksforgeeks.org/)
