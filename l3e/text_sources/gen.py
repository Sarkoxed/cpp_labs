from random import randint, random
from numpy.random import permutation
l = ["k1ll3r", "n00bf1ght3r", "sc0rp10n", "G4uss", "Euler", "faust", "Slave", "Slava", "Mir0n", "N33d4sp33d", "Pirate", "parrot", "elon_Tusk", "tom_hard", "m00n", "sarkoxed", "ne_bknn", "anzan", "agalas", "voltarcarnage", "e1vo", "mc_batrudinov", "mc_borrow", "fathich", "potap_no_nastya", "P0t4p_4nd_Nastya", "Zamay", "leon", "kirk_hammet", "tom_newyork", "albanskij_ubijca", "hunting_strong", "kven", "dmitry_utkin", "UslessMoouth", "MARK", "Billy_Herrington", "Vladimir_Pluto", "whiplash", "DRAGONFLY", "loqiememe", "twilight_sparkle", "edward", "n0rton", "boris_the_blade", "aquadisco", "bipolar", "spider", "Jeff", "Bezos", "The_House", "That_Jack_built", "Eduard_Limonov", "J0ker", "One_sailor", "Another_sailor", "Chris-reker", "obezjanking", "svtv_anime_opening", "straw_raccon", "straw", "sonya_marmeladova", "birds_ash", "Naruto", "John_snow", "maybe-baby", "Angel_of_consolation", "Garry_the_axe", "Tommy", "Turkish", "Mickey", "Tony_Bullet_Tooth", "Dora", "door", "God_Blesser", "Pyro", "Dangeon_master", "GOON", "H34DSH00t", "2pac", "Led_zeppelin", "Yagami_Light", "C0wB0y", "Beebop", "Seryoga", "Lexa", "Arthas", "Angry_Bird", "cal_el", "shoegaze", "bizkit", "BRZRKR", "Berserk", "Vorovskaya_lapa", "Sax_Guy", "Turing", "Ti_lox", "S4lk3r_pl4ay3r", "I_LOVE_MY_MOM", "LOVE", "Love_sausage", "GAS_SECTOR", "RobotChicken", "K1ller_Ub1v3c", "Zahych2014", "I_LOVE_WOT", "Garik_bulldog", "White_nights", "Interstellar", "Gypsy", "I_HATE_GYPSIES", "Winner", "EMI1", "BgcH", "Demolish_Master", "JOB", "JOB-2", "JOB-3", "jojo<3", "pon", "ponpon", "Arolf", "Toxin", "society_person", "Jirid", "Britney_Spears", "Zinler", "Ya_Tyan!", "XX_KING_XX", "Kirk_Lazarus", "Les_Grossman", "Grazix", "Koroleva))))", ""]
print(len(l))  

n = ["228", "1337", "1488", "119", "11956", "1917", "1703", "2005", "1993", "1000-7", "2024", "8", "40407", "3647b", "42", "<3", "))))))", ")00))00)", ":)", ":(", ":/", "!!!"]

z = list(permutation(len(l)))
m = [l[x] for x in z]
ans = []
for i in range(len(m)):
    ans.append(dict())
    ans[i].setdefault("name", m[i])
    ans[i].setdefault("kind", "rooster")
    ans[i].setdefault("total fights", 0)
    ans[i].setdefault("total wins", 0)
    ans[i].setdefault("winrate", 0)
    if(random() < 0.3):
        ans[i]["name"] = ans[i]["name"] + n[randint(0, len(n)-1)]
    ans[i] = str(ans[i])
f = open("players", "wt")
f.write("\n".join(ans))
f.close()        
       
