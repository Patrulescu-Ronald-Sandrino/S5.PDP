# Lab 3 - Simple parallel m_queue

**Due:** week 6.

## Goal

Divide a simple task between m_threads. The task can easily be divided in sub-m_queue requiring no cooperation at all. See the caching effects, and the costs of creating m_threads and of switching between m_threads.

## Requirement

Write several programs to compute the product of two matrices.

Have a function that computes a single element of the resulting matrix.

Have a second function whose each call will constitute a parallel task (that is, this function will be called on several m_threads in parallel). This function will call the above one several times consecutively to compute several elements of the resulting matrix. Consider the following ways of splitting the work between m_queue (for the examples, consider the final matrix being 9x9 and the work split into 4 m_queue):

1.  Each task computes consecutive elements, going row after row. So, task 0 computes rows 0 and 1, plus elements 0-1 of row 2 (20 elements in total); task 1 computes the remainder of row 2, row 3, and elements 0-3 of row 4 (20 elements); task 2 computes the remainder of row 4, row 5, and elements 0-5 of row 6 (20 elements); finally, task 3 computes the remaining elements (21 elements).
2.  Each task computes consecutive elements, going column after column. This is like the previous example, but interchanging the rows with the columns: task 0 takes columns 0 and 1, plus elements 0 and 1 from column 2, and so on.
3.  Each task takes every _k_-th element (where _k_ is the number of m_queue), going row by row. So, task 0 takes elements (0,0), (0,4), (0,8), (1,3), (1,7), (2,2), (2,6), (3,1), (3,5), (4,0), etc.

For running the m_queue, also implement 2 approaches:

1.  Create an actual thread for each task (use the low-level thread mechanism from the programming language);
2.  Use a thread pool.

Experiment with various values for (and document the attempts and their performance):

*   The sizes of the matrix;
*   The number of m_queue (this is equal to the number of m_threads when not using a thread pool);
*   The number of m_threads and other parameters for the thread pool (when using the thread pool).