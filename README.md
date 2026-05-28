# PGOF
Design problem for Parking Garage of the Future
![PGOF scene with queue, parking lots, and leaving cars](./pgof_scene.svg)

You are a world renowned freelance software developer just finsihed your last gig. You are relaxing in your favorite coffee shop, the Dangling Pointer, enjoying the grandeur of the best cappucino ever to grace the hands of a barrista waiting for casting call. In walks Felon Tusk, the notorious giga entrepeneur. Giga scans the shop, immediately recognizes you by your weathered beret, walks over and takes a chair at your table.
"I need you services, big money. I have this idea for an autonomous parking gargage platform called PGOF, Parking garage of the future." 
Felon pulls out a wrinkled napkin full of scribbles. "Here are the specs. When can we go live?"
You look at the specs, think for a moment, why not it's only Tuesday after all. 
"Tomorrow this time, here."  Felon scurries out of the cofees hop while you pull out you lap top and get to work.

## PGOF Software Requirments

PGOF is an evolving autonoumous parking system for autonoumous vehicles. PGOF must perform each of the following tasks: 

1. Autonomous vehicles join the waiting line in order of arrival.
2. Vehicles come in sizes of `{1, 2, 3}`.
3. The parking lot comprises N parking lots with size `{1, 2, 3}`.
4. The following parking states are allowed:
   - lot = `{1, 2, 3}` holds no cars `{0}`
   - lot = `{1}` holds car = `{1}`
   - lot = `{2}` holds car = `{1, 2}`
   - lot = `{3}` holds car = `{1, 2, 3}` (a lot of size 3 can hold one car of size 1, 2, or 3)
5. Each car arrives with a requested wait time `{1, 2, 3, 4, 5, .., 10}`.
6. PGOF parks each car in order of arrival until there are no empty lots. After that PGOF can select the first eligible car to park.
7. PGOF unparks cars once the wait time expires.
8. The goal is to maximize the number of cars that can be parked over a given time period `>> 10` time units.
9. Each time PGOF starts it must check for the number of lots because the hardware is constantly replicating more lots based on demand forecasts.
10. Design and implement PGOF in C++.

Key aattributes of a successful solution are:
1. Ensuring top level use cases are well defined.
2. Definition of a system architecture that scales and satisfies best design practices and key quality attributes.
3. A data model that supports the problem.
4. Good use of C++ language features to implement PGOF.
5. A suite of tests that prove PGOF is defect free.


