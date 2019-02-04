# ft_ls
A partial re-implementation of the unix "ls" command implemented in C.

## Description
The goal of this project is to discover a sub-system of functions of operating system’s API, the associated data structures, as well as the management of memory allocation and the associated data.

The implemented functionality closely mocks the behaviour found in `man ls`.

For a more thorough description and list of requirements (such as allowed functions) look at "ft_ls.en.pdf".

### Functionality
The command has the following usage:
`ft_ls [-alrRt] [files ...]`

#### Supported flags:
`-a` : Include hidden directory entries.

`-l` : List in long format.

`-r` : Reverse the order of the sort.

`-R` : Recursively list subdirectroies encountered.

`-t` : Sort by time modified (most recently modified first) before sorting the operands by lexicographical order.

### Usage
```
$ make
```

```
$ ./ft_ls [command flags ...] [files ...]
```
