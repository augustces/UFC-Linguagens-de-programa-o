ocorrencia [] p q = []
ocorrencia (x:xs) p q 
    | x == p = (p+q):ocorrencia xs p q
    | otherwise = x:ocorrencia xs p q


transformarInt = map (\x -> read x::Int)

transformarStr [] = [" "]
transformarStr xs = map(\x -> show x) xs

main = do
    c1 <- getLine
    c2 <- getLine 
    putStrLn $ unwords . transformarStr $ ocorrencia (transformarInt (words c1)) (head (transformarInt (words c2))) (last (transformarInt (words c2)))