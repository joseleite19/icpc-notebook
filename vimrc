set ts=4 sw=4 sta nu rnu sc stl+=%F cindent
set bg=dark ruler timeoutlen=1000
set viminfo='20,\"1000
imap {<CR> {<CR>}<Esc>O
nmap <F2> 0V$%d
nmap <C-down> :m+1<CR>
nmap <C-up> :m-2<CR>
nmap <C-a> ggVG
nmap <S-up> :m-2<CR>
nmap <S-down> :m+1<CR>
vmap <C-c> "+y
syntax on

set timeoutlen=1000
