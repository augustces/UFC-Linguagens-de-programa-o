primo n
    | n <= 1 = False 
    | otherwise = foldl (\acc x ->  acc && mod n x /= 0 )True [2.. n - 1]

ehPrimo [] = []
ehPrimo (x:xs) = condicao x ++ ehPrimo xs
    where condicao x = [x | primo x]

transformarInt = map(\x -> read x::Int)

transformarStr [] = [" "]
transformarStr xs = map(\x -> show x) xs

main = do
    c1 <- getLine
    putStrLn $ unwords . transformarStr $ ehPrimo (transformarInt (words c1))