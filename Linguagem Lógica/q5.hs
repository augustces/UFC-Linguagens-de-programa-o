retangulo (x,y,largura, altura) (px, py)
    | condicao1 && condicao2 = putStrLn "sim"
    | otherwise = putStrLn "nao"
    where 
        condicao1 = px > x && py > y
        condicao2 = py < y + altura && px < x + largura

transformar c = map(\x -> read x::Int) (words c)
main = do
    c1 <- getLine
    c2 <- getLine
    retangulo (head (transformar c1), head (tail $ transformar c1), last (init $ transformar c1), last $ transformar c1) (head $ transformar c2, last $ transformar c2)