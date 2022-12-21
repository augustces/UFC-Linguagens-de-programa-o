remover [] x = []
remover (y:ys) x
    | y == x = ys
    | otherwise = y: remover ys x

dif [] y = []
dif x [] = x
dif (x:xs) ys
    | elem x ys = dif xs (remover ys x)
    | otherwise = x:dif xs ys

divide list =  
    case list of
        [] -> ([], [])
        x:xs -> 
            let (odds, evens) = divide xs
            in (x:evens, odds)

merge ([], y) = y                   
merge (x, []) = x                   
merge (a:x, b:y)                    
  | a <= b    = a:merge (x, b:y)    
  | otherwise = b:merge (a:x, y)    

mergeSort [] = []
mergeSort [x] = [x]
mergeSort x = merge (mergeSort p, mergeSort q)
    where (p,q) = divide x

uniao x [] = x
uniao x (y:ys) 
    | elem y x = uniao x ys
    | otherwise = uniao x ys ++ [y]

difSim x y = mergeSort $ uniao (dif x y) (dif y x)

transformarInt = map (\x -> read x::Int)

transformarStr [] = [" "]
transformarStr xs = map(\x -> show x) xs

main = do
    c1 <- getLine
    c2 <- getLine 
    putStrLn $ unwords . transformarStr $ difSim (transformarInt (words c1)) (transformarInt (words c2))