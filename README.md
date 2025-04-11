<h2>Class Scheduling Problem for CSCE 3110</h2>

<h3>Introduction</h3>
<p>This project addresses the class scheduling problem by considering the courses students want to take while ensuring that classes do not overlap. The scheduling algorithm takes into account both the days and times of the courses. To efficiently select non-overlapping courses, we use a Greedy Algorithm approach.</p>

<h3>Data Structure</h3>
<p>Hash map and vectors have been used to store and filter out appropriate classes.<p>
<ul>
  <li><strong>Hash map:</strong> Used to store all class data, including course ID, class name, days, time, and location. It allows for quick access and organization, using the course ID as the key.</li>
  <li><strong>Vector:</strong> Used to store classes that match the user's preferences, as well as to hold the final suggested schedules.</li>
</ul>

<h3>Algorithm</h3>
<p>A Greedy Algorithm is an approach that makes the best local decision at each step, hoping to find an optimal solution. For class scheduling, it selects courses one by one while ensuring they do not overlap in time.</p>
<ol>
  How it works:
  <li>Sort Courses → Courses are sorted by start time, end time, or duration (usually by end time for best results).</li>
  <li>Iterate Through Courses → Loop through the list of courses.</li>
  <li>Check for Overlaps → For each course, check if it conflicts with already scheduled courses.</li>
  <li>Schedule If Possible → If a course does not overlap, add it to the schedule.</li>
  <li>Update the Latest End Time → Keep track of the latest end time for each day to prevent conflicts.</li>
</ol>

<h3>Team Members</h3>
<ul>
  <li>Emmitt Singh</li>
  <li>Linal Lad</li>
  <li>Trinh Tran</li>
</ul>

## How To Run The Program

```bash
g++ main.cpp classes.cpp schedule.cpp -o scheduler
./scheduler
```
