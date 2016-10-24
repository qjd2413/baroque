# baroque
an esoteric program interpreter that translates musical notation to machine language

### Humdrum \*\*kern
baroque reads music scores represented in the [Humdrum \*\*kern format](http://www.music-cog.ohio-state.edu/Humdrum/representations/kern.html). Below are the first two measures of Haydn's Minuetto 4 from String Quartet in G major (which happens to translate to a multiply instruction in baroque).
```
**kern  **kern  **kern  **kern
*k[f#]  *k[f#]  *k[f#]  *k[f#]
*G: *G: *G: *G:
*clefF4 *clefC3 *clefG2 *clefG2
*M3/4   *M3/4   *M3/4   *M3/4
4GG 4G  4.G 4.g
4B  4b  .   .
.   .   8A  8a
4G  4g  4B  4b
=2  =2  =2  =2
4A  4a  4c  4cc
4F# 4f# 4A  4a
4D  4d  4A  4a
==  ==  ==  ==
*-  *-  *-  *-
```
