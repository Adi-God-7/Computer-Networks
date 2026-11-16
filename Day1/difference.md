# Code differences

## 1. Removed unnecessary `else` blocks

Old server structure:

```c
if(r<0) {
    ...
}
else {
    ...
}
```

New server structure:

```c
if(r<0) {
    ...
    exit(1);
}
buff[r]='\0';
```

**Benefit:** Once an error exits the program, the `else` block is unnecessary. The normal code can continue at the next line, making the flow easier to read.

## 2. Removed temporary `bind` and `listen` variables

Old:

```c
int b=bind(listenfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
if(b<0) {
    ...
}
c=listen(listenfd,5);
if(c<0) {
    ...
}
```

New:

```c
if(bind(listenfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0) {
    ...
}
if(listen(listenfd,5)<0) {
    ...
}
```

**Benefit:** `b` and `c` were used only once, so removing them reduces variables without changing behavior.

## 3. Removed the unnecessary send/receive status variables in the client

Old:

```c
w=send(skfd,sbuff,strlen(sbuff),0);
if(w<0)
```

New:

```c
if(send(skfd,sbuff,strlen(sbuff),0)<0)
```

**Benefit:** The client only needs to know whether sending failed; it does not use the returned byte count afterward.

## 4. Improved client receive validation

Old:

```c
if(r<0)
```

New:

```c
if(r<=0)
```

**Benefit:** `recv()` returning `0` means the server closed the connection. Treating it as an error prevents printing an empty response as if it were valid.

## 5. Corrected cleanup on server write failure

New server code closes both `connfd` and `listenfd` when writing fails.

**Benefit:** This releases both socket resources on that error path.
