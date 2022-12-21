palindromo [] = True
palindromo [x] = True
palindromo (x:xs)
    | x == last xs = palindromo (init xs)
    | otherwise = False

subPalin n [] = False
subPalin n w 
    | length w < n = False
    | otherwise = palindromo w || subPalin n (init w) || subPalin n (init $ tail w) || subPalin n (tail w)

ehPalindromo n w
    | subPalin n w = putStrLn "sim"
    | otherwise = putStrLn "nao"


transformarInt x = read x::Int

main = do
    n <- getLine
    str <- getLine 
    ehPalindromo (transformarInt n) str