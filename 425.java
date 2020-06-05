class Solution {
    class TrieNode {
        TrieNode[] children;
        boolean isWord;
        
        TrieNode() {
            children = new TrieNode[26];
        }
    }
    
    public List<List<String>> wordSquares(String[] words) {
        TrieNode root = buildTrie(words);
        List<List<String>> squares = new ArrayList<>();
        
        for (String word : words) {
            List<String> square = new ArrayList<>();
            square.add(word);
            wordSquares(root, word.length(), square, squares);
        }
        return squares;
    }
    
    private TrieNode buildTrie(String[] words) {
        TrieNode root = new TrieNode();
        for (String word : words) {
            TrieNode current = root;
            for (char c : word.toCharArray()) {
                int index = c - 'a';
                if (current.children[index] == null) {
                    current.children[index] = new TrieNode();
                }
                current = current.children[index];
            }
            current.isWord = true;
        }
        return root;
    }
    
    private TrieNode search(TrieNode root, String prefix) {
        TrieNode current = root;
        for (char c : prefix.toCharArray()) {
            int index = c - 'a';
            if (current.children[index] == null) {
                return null;
            }
            current = current.children[index];
        }
        return current;
    }
    
    private void wordSquares(TrieNode root, int len, List<String> square, List<List<String>> squares) {
        if (square.size() == len) {
            squares.add(new ArrayList<>(square));
            return;
        }

        String prefix = getPrefix(square, square.size());
        TrieNode node = search(root, prefix);
        if (node == null) {
            return;
        }
        
        List<String> children = new ArrayList<>();
        getChildren(node, prefix, children);
        for (String child : children) {
            square.add(child);
            wordSquares(root, len, square, squares);
            square.remove(square.size() - 1);
        }
    }
    
    private String getPrefix(List<String> square, int index) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < index; i++) {
            sb.append(square.get(i).charAt(index));
        }
        return sb.toString();
    }
    
    private void getChildren(TrieNode node, String s, List<String> children) {
        if (node.isWord) {
            children.add(s);
            return;
        }
        
        for (int i = 0; i < 26; i++) {
            if (node.children[i] != null) {
                getChildren(node.children[i], s + (char) ('a' + i), children);
            }
        }
    }
}

/*
https://zhuhan0.blogspot.com/2017/09/leetcode-425-word-squares.html

Thought process:
Store all words into a trie. Iterate through the words.
- For each word:
    - create a new list. Add the word into the list.
    - Search the trie for all the words that have the correct prefix. For each of these words:
        - Add it to the list.
        - Continue searching for the next prefix recursively.
        - The recursion reaches its base case when the size of the list is equal to the length of a word. In this case, we've found a word square.

Time complexity:
Say there are n words, the words' length is l, and each trie node has c children on average. buildTrie() takes O(ln). wordSquares() helper method takes O(c^l). So the for loop takes O(nc^l). The overall time complexity is O(ln + nc^l).

*/
