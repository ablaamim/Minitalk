---

_The purpose of this project is to code a small data exchange program using UNIX **signals**._

<details>

### What is a signal?

>A signal is a notification to a **process** that an event has occurred. Signals are sometimes described as software interrupts.
>
>One process can send a signal to another process. In this use, signals can be employed as a primitive form of interprocess communication (IPC). 
>
>Each signal is defined as a unique (small) integer, starting sequentially from 1. These integers are defined in <signal.h> with symbolic names of the form SIGxxxx. Since the actual numbers used for each signal vary across implementations, it is these symbolic names that are always used in programs. 
>
>A signal is said to be _generated_ by some event. Once generated, a signal is later _delivered_ to a process, which then takes some action in response to the signal. Between the time it is generated and the time it is delivered, a signal is said to be _pending_.

### What is a process?

>A process is an instance of an executing **program**.
>
>We can recast the definition of a process given at the start of this section as follows: a process is an abstract entity, defined by the kernel, to which system resources are allocated in order to execute a program.
>
>From the kernel’s point of view, a process consists of user-space memory containing program code and variables used by that code, and a range of kernel data structures that maintain information about the state of the process. The information recorded in the kernel data structures includes various identifier numbers
(IDs) associated with the process, virtual memory tables, the table of open file descriptors, information relating to signal delivery and handling, process resource usages and limits, the current working directory, and a host of other information.

### What is a program?

>A program is a file containing a range of information that describes how to construct a process at run time. One program may be used to construct many processes, or, put conversely, many processes may be running the same program.
	
</details>

---

_You must create a communication program in the form of a **client** and a **server**._

<details>
	
### What is a client-server application?

>A client-server application is one that is broken into two component processes:
>
>- a client, which asks the server to carry out some service by sending it a request message; and
>- a server, which examines the client’s request, performs appropriate actions, and
then sends a response message back to the client.
>
>Sometimes, the client and server may engage in an extended dialogue of requests
and responses.
>
>Typically, the client application interacts with a user, while the server application provides access to some shared resource. Commonly, there are multiple
instances of client processes communicating with one or a few instances of the
server process.

</details>

---

_The server must be started first. After its launch, it has to print its **PID**._
	
<details>

### What is PID?

>Each process has a process ID (PID), a positive integer that uniquely identifies the process on the system. Process IDs are used and returned by a variety of system calls. For example, the kill() system call allows the caller to send a signal to a process with a specific process ID.
>
>The **getpid()** system call returns the process ID of the calling process. The pid_t data type used for the return value of getpid() is an integer type specified by SUSv3 for the purpose of storing process IDs.

```C
int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
```

</details>

---
	
_The client takes two parameters:_
- _The server PID._
- _The string to send._

<details>

```C
int	main(int argc, char *argv[])
{
	(void) argv;
	if (argc != 3)
	{
		ft_putendl_fd("Usage: ./client server-PID string-to-send", 1);
		exit(EXIT_FAILURE);
	}
	return (0);
}
```

</details>

---
	
_The client must **send the string passed as a parameter to the server**._
	
_The **communication** between your client and your server has to be done only using UNIX signals._
	
_You can only use these two signals: **SIGUSR1** and **SIGUSR2**._
	
<details>
