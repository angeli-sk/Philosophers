# Philosophers

It's a project to show the understanding of multithreading! You have an amount of philosophers around a table and they all have one fork.
They will need to lend a fork from another, since they're only allowed to eat with two forks. But they need to eat and sleep which al takes certain times that you set at the start of the program as an argument.
Spoiler alert:
The philiosphers are all threads and the forks work with mutex locks so you can't grab a fork that's in use.

Usage:
./philo {PHILOSOPHERS_NUMBER} {TIME_THEY_WILL_DIE_IF_NO_FOOD} {TIME_TO_EAT} {TIME_TO_SLEEP}

Note:
If you want the philosphers to all have their own color, just find the comments and comment them in. It will be a beautiful rainbow on your screen.
I commneted it out as it sadly slowed down the performance of the philosophers, which would sometimes make them die when they shouldve survived it. Depeneding on your hardware ofcourse.

UwU
