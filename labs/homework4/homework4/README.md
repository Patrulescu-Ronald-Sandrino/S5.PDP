<h1 style="text-align: center;">Lab 4 - Futures and continuations</h1>

**Due:** <del>week 8</del> <ins>week 9, with bonus (1p) for having it finished by week 8</ins>

## Goal

The goal of this lab is to use C# TPL futures and continuations in a more complex scenario, in conjunction with waiting for external events.

## Requirement

Write a program that is capable of simultaneously downloading several files through HTTP. Use directly the BeginConnect()/EndConnect(), BeginSend()/EndSend() and BeginReceive()/EndReceive() Socket functions, and write a simple parser for the HTTP protocol (it should be able only to get the header lines and to understand the _Content-lenght:_ header line).

Try three implementations:

1.  Directly implement the parser on the callbacks (event-driven);
2.  Wrap the connect/send/receive operations in tasks, with the callback setting the result of the task;
3.  Like the previous, but also use the async/await mechanism.

## Examples

[srv-begin-end.cs](progs/srv-begin-end.cs)

[srv-task.cs](progs/srv-task.cs)

[srv-await.cs](progs/srv-await.cs)

A client for the above servers: [srv-client.cs](progs/srv-client.cs)
