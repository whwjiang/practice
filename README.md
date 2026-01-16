Here lies Squidward's hopes and dreams

# Usage
Use the prepare script to generate boilerplate for problems from various online judges. 

## Supported OJ
- Codeforces
- CSES
- USACO
- IOI
- NOI

This represents a majority of problems discussed in usaco.guide, so I haven't expanded it to any other online judges.

## Example
```sh
./prepare cses bit_inversions
```
Using the prepare script with ioi or cses will read from stdin and print to stdout.
Using the prepare script with usaco will call `freopen` on `cin` with the problem name. Use this for the filename given in the "input format" section of the USACO problem statement.
