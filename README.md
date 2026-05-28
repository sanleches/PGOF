# PGOF

Design problem for Parking Garage of the Future

You are a world renowned freelance software developer, just finished a crazy wild gig. You are relaxing in your favorite coffee shop, the Dangling Pointer, enjoying the grandeur of the best cappucino ever to grace the desperate hands of a barrista waiting for casting call. In walks Felon Tusk, the notorious giga entrepeneur. Felon scans the shop, immediately recognizes you by your weathered beret, walks over and takes a chair at your table. "I need your services, big money. I have this idea for an autonomous parking gargage platform called PGOF, Parking garage of the future." 
Felon pulls out a wrinkled napkin full of scribbles. "Here are the specs. When can we go live?" You look at the specs, think for a moment. Why not, it's only Tuesday after all. 
You reply, "Tomorrow this time, here."  Felon nods curtly and scurries out of the coffee shop; while you pull out your lap top and get to work ...

## PGOF Software Requirments
![PGOF scene with queue, parking lots, and leaving cars](PGOF.drawio.svg)
PGOF is an evolving autonoumous parking system for autonoumous vehicles. PGOF must perform each of the following tasks: 

1. Each time PGOF starts it must check for the number of lots because the hardware is constantly replicating more lots based on demand forecasts.
2. Autonomous vehicles join the waiting line in order of arrival.
3. Vehicles come in sizes of `{1, 2, 3}`.
4. Each car arrives with a requested wait time `{1, 2, 3, 4, 5, .., 10}`.
5. The parking lot comprises N parking lots with size `{1, 2, 3}`.
6. The following parking states are allowed:
   - lot = `{1, 2, 3}` holds no cars `{0}`
   - lot = `{1}` holds car = `{1}`
   - lot = `{2}` holds car = `{1, 2}`
   - lot = `{3}` holds car = `{1, 2, 3}` (e.g. a lot of size 3 can hold one car of size 1, 2, or 3)
7. PGOF parks each car in order of arrival until there are no empty lots. After that PGOF can select the first eligible car to park.  PGOF returns to first in logic once slot are available.
8. PGOF unparks cars once the wait time expires.
9. The goal is to maximize the fee for cars parked over a given time period `>> 10` time units. The fee structure is fee = car_size * parking_time (e.g. parking a car of size 3 for 2 time units costs $6)
10. Maintain running sum of fee collected each time a car is parked.
11. Maintain a runing count of the total number of cars parked
12. Design and implement PGOF in C++.

## Key aattributes of a successful solution are:

1. Ensuring top level use cases are well defined.
2. Definition of a system architecture that scales and satisfies best design practices and key quality attributes.
3. A data model that supports the problem.
4. Good use of C++ language features to implement PGOF.
5. A suite of tests that prove PGOF is defect free.


